
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14194.4 | 0.144796 | 440.477ms | 65103 | 320 | 12836.1 | 4374.06 | 0.0214286 | 0.212234 | 1(Win) | true |
| simdjson (stage-1) | 13392.1 | 0.0827623 | 467.261ms | 65103 | 2560 | 37688.5 | 4636.09 | 0.0910808 | 0.225041 | 2(Loss) | true |
