
----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9164.15 | 0.0255404 | 1654.52ms | 152326 | 40 | 655.661 | 15851.9 | 0.235221 | 0.269714 | 1(Win) | true |
| simdjson (ondemand) | 7918.19 | 0.354587 | 1881.51ms | 152326 | 80 | 338557 | 18346.3 | 0.339173 | 0.312236 | 2(Loss) | true |
