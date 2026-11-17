
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2053.41 | 0.0885073 | 219.707ms | 4669 | 4890 | 18012.1 | 2168.45 | 0.09234 | 1.46655 | 1(Win) | true |
| Jsonifier (two-stage) | 1434.84 | 0.183649 | 314.86ms | 4669 | 640 | 20787.3 | 3103.28 | 0.115671 | 2.10263 | 2(Loss) | true |
| Glaze | 1249.04 | 0.0727808 | 357.881ms | 4669 | 4890 | 32918.4 | 3564.91 | 0.167758 | 2.42026 | 3(Loss) | true |
| simdjson (ondemand) | 804.986 | 0.146619 | 556.362ms | 4669 | 640 | 42095 | 5531.41 | 0.00847362 | 3.76145 | 4(Loss) | true |
