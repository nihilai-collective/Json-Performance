
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1296.2 | 1.66363 | 5969.2ms | 5373214 | 40 | 1.73019e+11 | 3.95332e+06 | 1.32131 | 1.91003 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1266.18 | 0.665422 | 6191.51ms | 5373214 | 40 | 2.90091e+10 | 4.04706e+06 | 0.182987 | 1.95532 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 428.345 | 3.27152 | 7914.74ms | 5373214 | 30 | 4.59515e+12 | 1.1963e+07 | 3.90769 | 5.77985 | -(Tie) | false |
| Glaze STATISTICAL TIE | 421.218 | 0.267145 | 8646.58ms | 5373214 | 30 | 3.16861e+10 | 1.21654e+07 | 0.819209 | 5.87777 | 3(Tie) | true |
