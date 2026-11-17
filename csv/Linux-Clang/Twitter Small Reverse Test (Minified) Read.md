
----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 844.862 | 0.099291 | 1038.02ms | 2821 | 40 | 399.866 | 3184.32 | 0.0206785 | 6.17817 | 26.1195 | 4.82985 | 0.00130273 | 3.54484e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 355.063 | 0.0750908 | 1482.21ms | 2821 | 1280 | 41436.1 | 7577 | 0.0746647 | 14.581 | 67.0255 | 11.5573 | 0.011511 | 7.5051e-05 | 1.46779e-05 | 2(Loss) | true |
