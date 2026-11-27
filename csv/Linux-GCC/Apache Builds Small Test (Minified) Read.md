
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2977.28 | 0.133246 | 798.627ms | 2632 | 320 | 403.825 | 843.075 | 0.118473 | 1.82084 | 7.07219 | 1.25 | 0.00076819 | 3.68066e-05 | 2.01843e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2018.92 | 0.504208 | 842.125ms | 2632 | 160 | 6287.45 | 1243.28 | 0.521497 | 2.6238 | 10.8469 | 1.69377 | 0.00078125 | 5.22416e-05 | 4.74924e-06 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2002.34 | 0.0456875 | 861.376ms | 2632 | 4890 | 1603.99 | 1253.57 | 0.217362 | 2.64495 | 11.0171 | 2.11968 | 0.000709919 | 5.76513e-05 | 1.82588e-05 | 2(Tie) | true |
| simdjson (reflection) | 1785.78 | 0.0555555 | 859.974ms | 2632 | 4890 | 2981.82 | 1405.59 | 0.0431534 | 2.96329 | 9.50456 | 1.56345 | 0.00211492 | 5.22902e-05 | 1.24315e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1732.37 | 0.102603 | 871.86ms | 2632 | 2560 | 5657.84 | 1448.92 | 0.294367 | 3.05117 | 10.3822 | 1.95023 | 0.00167322 | 6.97545e-05 | 1.63255e-05 | 5(Loss) | true |
