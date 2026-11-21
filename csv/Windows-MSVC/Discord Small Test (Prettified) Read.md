
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1118.09 | 0.123663 | 586.311ms | 6701 | 160 | 7993.32 | 5715.62 | 0.0985114 | 2.20538 | 1(Win) | true |
| Jsonifier | 1101.11 | 0.103489 | 600.756ms | 6701 | 160 | 5772.01 | 5803.75 | 0.236356 | 2.23731 | 2(Loss) | true |
| Glaze | 1048.48 | 0.499392 | 624.234ms | 6701 | 1280 | 1.18591e+06 | 6095.08 | 0.198281 | 2.35067 | 3(Loss) | true |
| simdjson (ondemand) | 965.229 | 0.247323 | 671.041ms | 6701 | 2560 | 686414 | 6620.78 | 0.222523 | 2.55368 | 4(Loss) | true |
