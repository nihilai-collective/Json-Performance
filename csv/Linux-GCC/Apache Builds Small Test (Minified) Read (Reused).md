
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2565.33 | 0.408735 | 105.507ms | 2632 | 1280 | 20472.8 | 978.459 | 0.218373 | 0.937909 | 1(Win) | true |
| Jsonifier (two-stage) | 2259.1 | 0.0529445 | 123.39ms | 2632 | 160 | 55.3685 | 1111.09 | 0.311221 | 1.06881 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2008.19 | 0.125292 | 135.874ms | 2632 | 320 | 784.802 | 1249.92 | 0.950511 | 1.20587 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2008.16 | 0.282062 | 138.508ms | 2632 | 30 | 372.892 | 1249.93 | 0.19238 | 1.20483 | 3(Tie) | true |
| Glaze | 1969.27 | 0.114932 | 137.479ms | 2632 | 640 | 1373.49 | 1274.62 | 0.344668 | 1.23031 | 5(Loss) | true |
