
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20603.9 | 0.249811 | 400.525ms | 83958 | 4890 | 460850 | 3886.09 | 0.11044 | 0.11929 | 1(Win) | true |
| simdjson (stage-1) | 18420.7 | 0.213131 | 438.56ms | 83958 | 30 | 2574.71 | 4346.67 | 0.15361 | 0.133223 | 2(Loss) | true |
