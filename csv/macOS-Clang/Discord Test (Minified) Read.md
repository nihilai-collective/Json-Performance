
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2376.9 | 0.0680954 | 2330.04ms | 56369 | 30 | 7115.67 | 22616.7 | 0.0797982 | 1(Win) | true |
| Jsonifier (two-stage) | 1683.6 | 0.0374838 | 3251.27ms | 56369 | 80 | 11459.9 | 31930.2 | 0.0328734 | 2(Loss) | true |
| Glaze | 1567.63 | 0.0557705 | 3535.64ms | 56369 | 4890 | 1.78859e+06 | 34292.3 | 0.222957 | 3(Loss) | true |
| simdjson (ondemand) | 765.406 | 0.0446724 | 7277.59ms | 56369 | 4890 | 4.81377e+06 | 70234.2 | 0.189336 | 4(Loss) | true |
