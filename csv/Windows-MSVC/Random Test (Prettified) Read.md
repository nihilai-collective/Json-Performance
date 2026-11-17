
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20892.5 | 0.120453 | 3399.86ms | 728486 | 4890 | 7.84518e+06 | 33252.9 | 1.0566 | 0.118388 | 1(Win) | true |
| simdjson (stage-1) | 19492 | 0.304383 | 3579.16ms | 728486 | 2560 | 3.01307e+07 | 35642.1 | 0.476926 | 0.126899 | 2(Loss) | true |
