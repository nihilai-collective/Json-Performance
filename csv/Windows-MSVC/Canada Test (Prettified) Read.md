
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1183.74 | 1.33651 | 6556.31ms | 5373214 | 40 | 1.33894e+11 | 4.32889e+06 | 1.69614 | 2.0914 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1171.87 | 0.683716 | 6670.65ms | 5373214 | 80 | 7.1508e+10 | 4.37277e+06 | 1.34287 | 2.11263 | 1(Tie) | true |
| simdjson (ondemand) | 426.731 | 1.30684 | 8470.27ms | 5373214 | 30 | 7.38795e+11 | 1.20083e+07 | 0.298545 | 5.80176 | 3(Loss) | true |
| Glaze | 403.345 | 0.849082 | 9033.76ms | 5373214 | 40 | 4.6545e+11 | 1.27045e+07 | 1.9438 | 6.13821 | 4(Loss) | true |
