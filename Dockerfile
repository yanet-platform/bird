# syntax=docker/dockerfile:1

FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

RUN --mount=type=bind,source=.,target=/packages \
    apt-get update \
    && apt-get install -y --no-install-recommends /packages/yanet-bird2_*.deb \
    && printf '%s\n' \
        'log "/dev/stdout" all;' \
        'router id 127.0.0.1;' \
        'protocol device {}' > /etc/bird/bird.conf \
    && rm -rf /var/lib/apt/lists/*

COPY --chmod=755 <<'EOF' /usr/local/bin/bird-entrypoint
#!/bin/sh
set -eu
if [ "$#" -eq 1 ]; then
    case "$1" in
        --help|--version) exec /usr/sbin/bird "$@" ;;
    esac
fi

/usr/lib/bird/prepare-environment
exec /usr/sbin/bird -f "$@"
EOF

ENTRYPOINT ["/usr/local/bin/bird-entrypoint"]
CMD ["-c", "/etc/bird/bird.conf"]
