
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 250.621 | 0.185127 | 370.831ms | 905 | 80 | 3251.58 | 3443.75 | 0.474106 | 12.075 | 1(Win) | true |
| simdjson (ondemand) | 128.753 | 0.133494 | 727.881ms | 905 | 30 | 2402.3 | 6703.33 | 0.248016 | 23.536 | 2(Loss) | true |
