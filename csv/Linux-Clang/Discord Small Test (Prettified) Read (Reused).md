
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2884.27 | 0.137856 | 256.632ms | 6701 | 30 | 279.885 | 2215.67 | 0.121711 | 0.848296 | 1(Win) | true |
| Glaze | 2430.8 | 0.12063 | 290.785ms | 6701 | 30 | 301.724 | 2629 | 0.142208 | 1.00801 | 2(Loss) | true |
| Jsonifier | 2128.77 | 0.0892557 | 341.408ms | 6701 | 40 | 287.179 | 3002 | 0.108698 | 1.15302 | 3(Loss) | true |
| simdjson (ondemand) | 1218.22 | 0.112207 | 555.209ms | 6701 | 4890 | 169425 | 5245.82 | 0.137759 | 2.02142 | 4(Loss) | true |
