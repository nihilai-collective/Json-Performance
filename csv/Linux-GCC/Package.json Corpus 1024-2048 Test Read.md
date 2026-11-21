
----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8422.52 | 0.0255065 | 1776.72ms | 152326 | 40 | 774.153 | 17247.7 | 0.203872 | 0.293507 | 1(Win) | true |
| simdjson (ondemand) | 7753.75 | 0.1278 | 1877.69ms | 152326 | 2560 | 1.46767e+06 | 18735.4 | 0.0865218 | 0.318877 | 2(Loss) | true |
