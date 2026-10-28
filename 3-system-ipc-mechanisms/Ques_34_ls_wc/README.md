Compile each variant separately. `dup_pipeline.c` redirects stdout using `dup`; `dup2_pipeline.c` uses `dup2`; `fcntl_pipeline.c` uses `fcntl(F_DUPFD, ...)`. Each runs the equivalent of `ls -l | wc`.
