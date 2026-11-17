
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4101.65 | 0.393988 | 196.861ms | 7932 | 1280 | 67580.9 | 1844.27 | 0.131062 | 0.595147 | 1(Win) | true |
| Jsonifier | 2708.49 | 0.111724 | 285.01ms | 7932 | 30 | 292.093 | 2792.9 | 0.0489576 | 0.905539 | 2(Loss) | true |
| simdjson (reflection) | 2284.46 | 0.0829984 | 324.535ms | 7932 | 80 | 604.268 | 3311.31 | 0.0252985 | 1.0746 | 3(Loss) | true |
| Glaze | 2171.1 | 0.104107 | 352.132ms | 7932 | 30 | 394.717 | 3484.2 | 0.389765 | 1.13118 | 4(Loss) | true |
| simdjson (ondemand) | 1696.59 | 0.0883903 | 442.838ms | 7932 | 160 | 2485.08 | 4458.67 | 0.496859 | 1.4504 | 5(Loss) | true |
