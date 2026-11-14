
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 995.563 | 0.441527 | 5543.41ms | 94653 | 2560 | 4.10285e+08 | 90670.4 | 0.250971 | 1(Win) | true |
| simdjson (ondemand) | 575.262 | 0.142534 | 9017.83ms | 94653 | 2560 | 1.2806e+08 | 156917 | 0.954873 | 2(Loss) | true |
