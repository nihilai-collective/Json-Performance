
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1731.54 | 0.17444 | 3465.63ms | 56369 | 640 | 1.8771e+06 | 31046.2 | 0.20983 | 1.42857 | 1(Win) | true |
| simdjson (ondemand) | 1403.01 | 0.0580381 | 4148.15ms | 56369 | 4890 | 2.41822e+06 | 38316 | 0.260886 | 1.76318 | 2(Loss) | true |
