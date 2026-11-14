
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5923.24 | 0.266081 | 2929.23ms | 183677 | 2560 | 1.5851e+07 | 29573 | 1.24953 | 1(Win) | true |
| simdjson (stage-1) | 5305.93 | 0.219288 | 3209.1ms | 183677 | 4890 | 2.56286e+07 | 33013.6 | 0.311549 | 2(Loss) | true |
