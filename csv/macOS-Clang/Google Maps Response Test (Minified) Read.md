
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2212.5 | 0.0268821 | 554.609ms | 11812 | 320 | 599.456 | 5091.43 | 0.0057078 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.2 | 0.0410333 | 942.645ms | 11812 | 80 | 1174.83 | 9339.1 | 0.0157913 | 2(Loss) | true |
| Glaze | 1051.45 | 0.0904039 | 1083.48ms | 11812 | 4890 | 458725 | 10713.6 | 0.453013 | 3(Loss) | true |
| simdjson (ondemand) | 805.6 | 0.0830197 | 1405.71ms | 11812 | 4890 | 658991 | 13983.1 | 0.116922 | 4(Loss) | true |
