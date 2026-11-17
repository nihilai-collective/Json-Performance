
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2956.08 | 0.223944 | 129.745ms | 3862 | 320 | 2491.28 | 1245.94 | 0.0250752 | 0.818986 | 1(Win) | true |
| simdjson (stage-1) | 606.021 | 0.110023 | 619.53ms | 3862 | 40 | 1788.46 | 6077.5 | 0.150602 | 4.05651 | 2(Loss) | true |
