
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2069.86 | 0.0684734 | 5565.93ms | 94653 | 2560 | 2.28281e+06 | 43610.6 | 0.103569 | 1.19541 | 1(Win) | true |
| simdjson (reflection) | 1805.75 | 0.0946286 | 6321.3ms | 94653 | 640 | 1.43212e+06 | 49989.3 | 0.100804 | 1.37036 | 2(Loss) | true |
| Jsonifier (two-stage) | 1735.39 | 0.127143 | 6310.36ms | 94653 | 2560 | 1.1197e+07 | 52016.2 | 0.0030203 | 1.42585 | 3(Loss) | true |
| simdjson (ondemand) | 1724.52 | 0.0599049 | 6390.52ms | 94653 | 4890 | 4.80805e+06 | 52344 | 0.0804931 | 1.43494 | 4(Loss) | true |
| Glaze | 1598.16 | 0.242075 | 6906.53ms | 94653 | 80 | 1.49561e+06 | 56482.5 | 0.00821118 | 1.54846 | 5(Loss) | true |
