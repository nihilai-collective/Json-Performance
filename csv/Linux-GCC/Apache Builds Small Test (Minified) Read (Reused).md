
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2265.13 | 0.162112 | 120.175ms | 2632 | 80 | 258.171 | 1108.14 | 0.156549 | 1.06793 | 1(Win) | true |
| Jsonifier (two-stage) | 2246.29 | 0.188018 | 121.578ms | 2632 | 4890 | 21584.9 | 1117.43 | 0.0415318 | 1.07405 | 2(Loss) | true |
| Jsonifier | 2231.17 | 0.0774212 | 122.44ms | 2632 | 30 | 22.7586 | 1125 | 0.0652277 | 1.08294 | 3(Loss) | true |
| simdjson (ondemand) | 1977.31 | 0.147606 | 134.873ms | 2632 | 160 | 561.757 | 1269.44 | 0.193608 | 1.22703 | 4(Loss) | true |
| Glaze | 1751.12 | 0.0457116 | 144.493ms | 2632 | 80 | 34.3467 | 1433.41 | 0.384299 | 1.38665 | 5(Loss) | true |
