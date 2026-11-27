
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2149.48 | 0.365785 | 10172.3ms | 7351818 | 80 | 1.13885e+10 | 3.26183e+06 | 0.329155 | 1.1518 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2148.43 | 1.06367 | 10140.6ms | 7351818 | 40 | 4.81973e+10 | 3.26343e+06 | 0.475472 | 1.15235 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 839.308 | 1.64355 | 5913.47ms | 7351818 | 40 | 7.54008e+11 | 8.3536e+06 | 2.73086 | 2.94982 | -(Loss) | false |
| Glaze | 708.62 | 0.395996 | 7015.38ms | 7351818 | 30 | 4.60538e+10 | 9.89421e+06 | 1.81783 | 3.49383 | 4(Loss) | true |
