
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 950.854 | 0.734865 | 9093.02ms | 2251027 | 160 | 4.40422e+10 | 2.2577e+06 | 0.825758 | 1(Win) | true |
| Jsonifier (two-stage) | 827.224 | 0.460915 | 5012.04ms | 2251027 | 80 | 1.14458e+10 | 2.59512e+06 | 0.369684 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 690.775 | 0.740049 | 5815.01ms | 2251027 | 40 | 2.11578e+10 | 3.10774e+06 | 1.62372 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 690.135 | 0.590168 | 5546.29ms | 2251027 | 40 | 1.34804e+10 | 3.11062e+06 | 0.639826 | 3(Tie) | true |
| simdjson (ondemand) | 582.427 | 0.779384 | 6281.36ms | 2251027 | 30 | 2.47572e+10 | 3.68586e+06 | 0.472663 | 5(Loss) | true |
