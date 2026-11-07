
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1413.12 | 0.366949 | 145.836ms | 1691 | 4890 | 85753.1 | 1141.21 | 0.0517019 | 1.70461 | 1(Win) | true |
| Jsonifier | 1300.86 | 0.279548 | 155.833ms | 1691 | 320 | 3843.16 | 1239.69 | 0.176145 | 1.86412 | 2(Loss) | true |
| Jsonifier (two-stage) | 1132.27 | 0.277972 | 173.355ms | 1691 | 4890 | 76647.3 | 1424.27 | 0.209603 | 2.14595 | 3(Loss) | true |
| simdjson (ondemand) | 704.412 | 0.131889 | 269.465ms | 1691 | 160 | 1458.73 | 2289.38 | 0.0273075 | 3.47585 | 4(Loss) | true |
