
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1757.06 | 0.104119 | 6855.68ms | 124597 | 1280 | 6.34619e+06 | 67627.2 | 0.0954868 | 1.40836 | 1(Win) | true |
| simdjson (ondemand) | 1584.21 | 0.0729628 | 7673.84ms | 124597 | 2560 | 7.66713e+06 | 75005.9 | 0.337213 | 1.56227 | 2(Loss) | true |
