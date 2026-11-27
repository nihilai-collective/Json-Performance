
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1533.34 | 0.878122 | 6047.84ms | 5373214 | 80 | 6.8896e+10 | 3.34193e+06 | 0.524214 | 1.6146 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1499.67 | 1.15078 | 6329.62ms | 5373214 | 40 | 6.18476e+10 | 3.41695e+06 | 1.97668 | 1.65088 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 492.755 | 1.07215 | 7680.43ms | 5373214 | 40 | 4.97257e+11 | 1.03993e+07 | 2.93644 | 5.0244 | -(Loss) | false |
| Glaze | 439.832 | 0.295667 | 8664.78ms | 5373214 | 30 | 3.55977e+10 | 1.16506e+07 | 1.17012 | 5.62884 | 4(Loss) | true |
