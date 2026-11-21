
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7741.87 | 0.089067 | 49.4355ms | 3808 | 320 | 55.8581 | 469.084 | 0.0526568 | 0.300641 | 1(Win) | true |
| Jsonifier (two-stage) | 7476 | 0.190545 | 52.9357ms | 3808 | 30 | 25.7023 | 485.767 | 0.206285 | 0.312903 | 2(Loss) | true |
| Jsonifier | 7354.12 | 0.0534843 | 53.9486ms | 3808 | 640 | 44.6441 | 493.817 | 0.0256229 | 0.319136 | 3(Loss) | true |
| Glaze | 3873.59 | 1.45672 | 117.975ms | 3808 | 640 | 119371 | 937.525 | 0.365317 | 0.621459 | 4(Loss) | true |
