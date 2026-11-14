
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23108.6 | 0.190372 | 464.506ms | 108313 | 30 | 2172.41 | 4470 | 0.0746269 | 0.10613 | 1(Win) | true |
| simdjson (stage-1) | 19898 | 0.0919099 | 528.923ms | 108313 | 80 | 1821.2 | 5191.25 | 0.0240848 | 0.123736 | 2(Loss) | true |
