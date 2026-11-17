
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 853.678 | 0.189794 | 470.149ms | 3873 | 30 | 2022.99 | 4326.67 | 0.38373 | 3.54109 | 1(Win) | true |
| simdjson (ondemand) | 563.973 | 0.114357 | 677.498ms | 3873 | 640 | 35899.2 | 6549.22 | 0.145321 | 5.37031 | 2(Loss) | true |
