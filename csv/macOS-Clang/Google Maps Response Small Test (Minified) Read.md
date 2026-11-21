
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2101.29 | 0.119939 | 204.989ms | 4390 | 4890 | 27924.8 | 1992.41 | 0.153817 | 1(Win) | true |
| Jsonifier (two-stage) | 1214.96 | 0.131569 | 352.847ms | 4390 | 30 | 616.645 | 3445.9 | 0.0406445 | 2(Loss) | true |
| Glaze | 984.94 | 0.221929 | 432.074ms | 4390 | 2560 | 227813 | 4250.64 | 0.517355 | 3(Loss) | true |
| simdjson (ondemand) | 785.602 | 0.125561 | 596.664ms | 4390 | 80 | 3582.01 | 5329.2 | 0.275187 | 4(Loss) | true |
