
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.706 | 0.211577 | 121.483ms | 905 | 320 | 1971.39 | 1173.12 | 0.265675 | 3.29781 | 1(Win) | true |
| simdjson (stage-1) | 137.865 | 0.271317 | 633.642ms | 905 | 2560 | 738550 | 6260.27 | 0.0143494 | 17.8051 | 2(Loss) | true |
