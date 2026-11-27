
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 189.479 | 0.260119 | 414.385ms | 905 | 40 | 5615.38 | 4555 | 6.14698 | 12.9777 | -(Win) | false |
| simdjson (ondemand) | 152.872 | 0.234941 | 570.712ms | 905 | 2560 | 450400 | 5645.74 | 0.143427 | 16.0873 | 2(Loss) | true |
