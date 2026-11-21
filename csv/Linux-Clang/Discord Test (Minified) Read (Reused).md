
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3043.49 | 0.0782992 | 2118.62ms | 56369 | 4890 | 935320 | 17663.2 | 0.0595769 | 0.812299 | 1(Win) | true |
| Jsonifier (two-stage) | 2413.21 | 0.0813925 | 2673.07ms | 56369 | 2560 | 841588 | 22276.4 | 0.0549379 | 1.02472 | 2(Loss) | true |
| Glaze | 2084.63 | 0.398709 | 2953.15ms | 56369 | 80 | 845721 | 25787.7 | 0.0666056 | 1.18648 | 3(Loss) | true |
| simdjson (ondemand) | 935.271 | 0.701337 | 6194.09ms | 56369 | 30 | 4.87506e+06 | 57478.2 | 0.384751 | 2.64594 | 4(Loss) | true |
