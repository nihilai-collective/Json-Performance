
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1294.2 | 0.730031 | 7990.79ms | 7351818 | 80 | 1.2513e+11 | 5.41744e+06 | 1.30871 | 2.34826 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1292.07 | 0.681333 | 7995.02ms | 7351818 | 40 | 5.4676e+10 | 5.42637e+06 | 0.571724 | 2.35197 | 1(Tie) | true |
