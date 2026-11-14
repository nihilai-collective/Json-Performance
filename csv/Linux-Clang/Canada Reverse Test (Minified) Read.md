
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 648.965 | 0.0962534 | 9725.02ms | 2090234 | 40 | 3.49655e+08 | 3.07166e+06 | 0.576007 | 3.81496 | 1(Win) | true |
| simdjson (ondemand) | 591.751 | 0.0926253 | 5044.77ms | 2090234 | 80 | 7.78862e+08 | 3.36865e+06 | 0.162623 | 4.18372 | 2(Loss) | true |
