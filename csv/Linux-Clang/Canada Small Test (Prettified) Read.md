
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1848.46 | 0.0549358 | 585.28ms | 11579 | 40 | 430.818 | 5973.95 | 0.363163 | 1.33311 | 1(Win) | true |
| Jsonifier | 1788.41 | 0.0345906 | 648.103ms | 11579 | 80 | 364.935 | 6174.54 | 0.327491 | 1.37861 | 2(Loss) | true |
| simdjson (ondemand) | 1673.86 | 0.119646 | 652.908ms | 11579 | 4890 | 304655 | 6597.1 | 0.0720784 | 1.47276 | 3(Loss) | true |
| Glaze | 1626.34 | 0.0687257 | 699.363ms | 11579 | 30 | 653.247 | 6789.83 | 0.0732021 | 1.51679 | 4(Loss) | true |
