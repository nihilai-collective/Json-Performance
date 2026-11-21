
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2528.68 | 0.099698 | 66.5849ms | 1691 | 80 | 32.3418 | 637.75 | 0 | 0.939762 | 1(Win) | true |
| Jsonifier (two-stage) | 2156.33 | 0.129991 | 77.4316ms | 1691 | 40 | 37.8045 | 747.875 | 0.233426 | 1.10547 | 2(Loss) | true |
| Glaze | 2066.66 | 0.0533721 | 80.9605ms | 1691 | 320 | 55.5042 | 780.322 | 0.0700342 | 1.15799 | 3(Loss) | true |
| simdjson (ondemand) | 1421.87 | 0.118323 | 115.872ms | 1691 | 80 | 144.078 | 1134.19 | 0.5731 | 1.70162 | 4(Loss) | true |
