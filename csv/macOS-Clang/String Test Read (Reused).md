
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 1207.14 | 0.286094 | 1137.1ms | 9578 | 640 | 299940 | 7566.91 | 1.06427 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 816.85 | 0.184306 | 1467.27ms | 9578 | 4890 | 2.07708e+06 | 11182.3 | 6.75184 | -(Loss) | false |
