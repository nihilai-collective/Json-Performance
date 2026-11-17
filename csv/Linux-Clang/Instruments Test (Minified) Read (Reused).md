
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3070.23 | 0.102279 | 3552.78ms | 108313 | 2560 | 3.03135e+06 | 33644.2 | 0.0864125 | 0.805729 | 1(Win) | true |
| Jsonifier (two-stage) | 2529.93 | 0.0722467 | 4280.67ms | 108313 | 4890 | 4.25491e+06 | 40829.4 | 0.429196 | 0.977926 | 2(Loss) | true |
| Glaze | 1742.21 | 0.0736006 | 6135.81ms | 108313 | 2560 | 4.8749e+06 | 59290 | 0.319954 | 1.42043 | 3(Loss) | true |
| simdjson (ondemand) | 675.665 | 0.148234 | 7926.39ms | 108313 | 2560 | 1.31473e+08 | 152880 | 0.274863 | 3.66356 | 4(Loss) | true |
