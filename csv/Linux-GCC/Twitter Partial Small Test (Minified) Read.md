
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7024.65 | 0.0480082 | 42.15ms | 2889 | 640 | 22.6912 | 392.214 | 0.0465887 | 0.329512 | 1(Win) | true |
| simdjson (reflection) | 6431.2 | 0.0776966 | 45.2586ms | 2889 | 160 | 17.727 | 428.406 | 0.173308 | 0.361113 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 6019.75 | 0.166166 | 48.5034ms | 2889 | 160 | 92.5432 | 457.688 | 0.00546254 | 0.387418 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6011.91 | 0.0747856 | 48.5384ms | 2889 | 640 | 75.1772 | 458.284 | 0.0878866 | 0.387742 | 3(Tie) | true |
| Glaze | 3158.93 | 0.0604864 | 90.8652ms | 2889 | 320 | 89.0599 | 872.184 | 0.043335 | 0.760508 | 5(Loss) | true |
