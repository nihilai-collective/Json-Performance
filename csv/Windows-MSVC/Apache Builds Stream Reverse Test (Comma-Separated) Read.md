
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 737.058 | 0.752192 | 6432.65ms | 4211999 | 30 | 5.04141e+10 | 5.44988e+06 | 7.88502 | 3.35889 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 727.06 | 2.13632 | 6725.07ms | 4211999 | 30 | 4.17915e+11 | 5.52482e+06 | 0.86589 | 3.40504 | 1(Tie) | true |
