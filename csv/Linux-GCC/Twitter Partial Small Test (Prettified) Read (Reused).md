
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7616.07 | 0.0883935 | 50.5882ms | 3808 | 640 | 113.698 | 476.833 | 0.016059 | 0.306469 | 1(Win) | true |
| Jsonifier (two-stage) | 7582.2 | 0.115403 | 51.1303ms | 3808 | 80 | 24.4416 | 478.962 | 0.101886 | 0.307888 | 2(Loss) | true |
| Jsonifier | 7271.91 | 0.207164 | 52.4596ms | 3808 | 30 | 32.1103 | 499.4 | 0.133672 | 0.321551 | 3(Loss) | true |
| simdjson (reflection) | 7205.05 | 0.0676963 | 53.1374ms | 3808 | 2560 | 298.05 | 504.034 | 0.303726 | 0.325142 | 4(Loss) | true |
| Glaze | 3873.03 | 0.0581958 | 96.9742ms | 3808 | 80 | 23.8214 | 937.663 | 0.238057 | 0.62071 | 5(Loss) | true |
