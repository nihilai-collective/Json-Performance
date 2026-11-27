
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2728.7 | 0.11974 | 68.0096ms | 1691 | 160 | 80.1258 | 591 | 0.254453 | 0.86298 | 1(Win) | true |
| Glaze | 2334.15 | 0.101389 | 78.0077ms | 1691 | 80 | 39.2557 | 690.9 | 0.23212 | 1.02161 | 2(Loss) | true |
| Jsonifier (two-stage) | 2108.5 | 0.0528446 | 90.8319ms | 1691 | 320 | 52.2745 | 764.837 | 0.14157 | 1.13435 | 3(Loss) | true |
| simdjson (reflection) | 1992.45 | 0.214069 | 87.6573ms | 1691 | 80 | 240.164 | 809.388 | 0.196521 | 1.19925 | 4(Loss) | true |
| simdjson (ondemand) | 1444.85 | 0.270666 | 121.303ms | 1691 | 2560 | 23364 | 1116.14 | 0.120073 | 1.67129 | 5(Loss) | true |
