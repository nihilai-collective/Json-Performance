
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 569.98 | 0.413823 | 230.177ms | 1313 | 320 | 26447.9 | 2196.88 | 0.399886 | 5.28782 | 1(Win) | true |
| simdjson (ondemand) | 321.896 | 0.0867677 | 397.239ms | 1313 | 80 | 911.392 | 3890 | 0.25641 | 9.36852 | 2(Loss) | true |
