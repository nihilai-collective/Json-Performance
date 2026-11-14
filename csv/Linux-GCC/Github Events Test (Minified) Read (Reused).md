
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2253.22 | 0.0496752 | 3571.03ms | 53331 | 2560 | 321863 | 22572.3 | 0.130389 | 2.2444 | 7.66137 | 1.22524 | 0.00743122 | 4.80197e-05 | 3.03163e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2048.13 | 0.0636333 | 3825.34ms | 53331 | 2560 | 639224 | 24832.6 | 0.110667 | 2.46893 | 8.52551 | 1.31658 | 0.00756815 | 5.84278e-05 | 3.62345e-05 | 2(Loss) | true |
| Glaze | 1961.04 | 0.0694963 | 3945.53ms | 53331 | 2560 | 831671 | 25935.5 | 0.0934047 | 2.5802 | 9.40842 | 1.77389 | 0.0155394 | 3.17592e-05 | 1.84285e-05 | 3(Loss) | true |
| simdjson (reflection) | 1875.19 | 0.0376671 | 4031.3ms | 53331 | 4890 | 510389 | 27122.8 | 0.125171 | 2.69079 | 8.97521 | 1.4671 | 0.00897948 | 9.40992e-05 | 6.58081e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1627.88 | 0.0234754 | 4410.04ms | 53331 | 4890 | 263056 | 31243.3 | 0.041879 | 3.10228 | 9.22399 | 1.63447 | 0.00955507 | 7.82435e-05 | 4.88365e-05 | 5(Loss) | true |
