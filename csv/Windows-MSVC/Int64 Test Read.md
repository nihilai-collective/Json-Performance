
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.919 | 0.164963 | 454.278ms | 3862 | 4890 | 264626 | 4459.39 | 0.367757 | 3.6635 | 1(Win) | true |
| simdjson (ondemand) | 579.216 | 0.0644859 | 657.596ms | 3862 | 160 | 2690.25 | 6358.75 | 0.857533 | 5.23491 | 2(Loss) | true |
