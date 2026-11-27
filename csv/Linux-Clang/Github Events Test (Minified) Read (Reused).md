
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2656.96 | 0.119545 | 2456.89ms | 53331 | 2560 | 1.34057e+06 | 19142.3 | 0.107054 | 0.930551 | 1(Win) | true |
| Jsonifier (two-stage) | 2044.01 | 0.0758101 | 2996.8ms | 53331 | 4890 | 1.74003e+06 | 24882.7 | 0.158897 | 1.20993 | 2(Loss) | true |
| Glaze | 1826.56 | 0.112549 | 3339.86ms | 53331 | 1280 | 1.25716e+06 | 27845 | 0.0430132 | 1.35417 | 3(Loss) | true |
| simdjson (ondemand) | 1141.63 | 0.108444 | 5089.49ms | 53331 | 640 | 1.49381e+06 | 44550.5 | 0.0793689 | 2.16739 | 4(Loss) | true |
