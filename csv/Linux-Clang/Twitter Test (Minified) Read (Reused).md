
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2099.6 | 0.491494 | 6383.98ms | 466906 | 40 | 4.34594e+07 | 212077 | 0.476724 | 1.17897 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2073.51 | 0.400114 | 5846.06ms | 466906 | 40 | 2.95308e+07 | 214746 | 0.429741 | 1.19383 | 1(Tie) | true |
| Glaze | 2003.19 | 0.309834 | 6422.61ms | 466906 | 80 | 3.79456e+07 | 222283 | 0.405348 | 1.23576 | 3(Loss) | true |
| simdjson (ondemand) | 957.568 | 0.133488 | 6261ms | 466906 | 320 | 1.23297e+08 | 465007 | 0.672252 | 2.5853 | 4(Loss) | true |
