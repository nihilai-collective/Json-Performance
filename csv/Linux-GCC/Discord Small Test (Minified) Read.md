
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1936.72 | 0.119333 | 241.334ms | 4857 | 30 | 244.368 | 2391.67 | 0.12699 | 1.2642 | 1(Win) | true |
| Glaze | 1624.3 | 0.542671 | 291.869ms | 4857 | 640 | 153269 | 2851.68 | 0.0590311 | 1.50973 | 2(Loss) | true |
| simdjson (reflection) | 1594.82 | 0.168461 | 307.873ms | 4857 | 30 | 718.179 | 2904.4 | 0.989739 | 1.53792 | 3(Loss) | true |
| Jsonifier (two-stage) | 1565.26 | 0.0927713 | 293.225ms | 4857 | 40 | 301.474 | 2959.25 | 0.398643 | 1.56618 | 4(Loss) | true |
| simdjson (ondemand) | 1338.97 | 0.148662 | 362.127ms | 4857 | 40 | 1057.93 | 3459.38 | 0.227194 | 1.83436 | 5(Loss) | true |
