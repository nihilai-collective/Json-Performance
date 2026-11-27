
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 429.02 | 0.787238 | 7974.12ms | 5212421 | 30 | 2.49607e+11 | 1.15868e+07 | 1.5293 | 5.77075 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 415.112 | 1.43041 | 8345.2ms | 5212421 | 30 | 8.80219e+11 | 1.1975e+07 | 0.718449 | 5.96417 | 1(Tie) | true |
