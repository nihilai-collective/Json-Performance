
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2299.5 | 0.118632 | 2925.69ms | 56369 | 4890 | 3.7612e+06 | 23378 | 1.11966 | 1(Win) | true |
| Glaze | 1827.28 | 0.100035 | 3450.37ms | 56369 | 4890 | 4.23525e+06 | 29419.5 | 0.466624 | 2(Loss) | true |
| Jsonifier (two-stage) | 1480.4 | 0.160656 | 4338.88ms | 56369 | 1280 | 4.35639e+06 | 36313 | 0.0599976 | 3(Loss) | true |
| simdjson (reflection) | 1092.03 | 0.738856 | 5635.05ms | 56369 | 160 | 2.11666e+07 | 49227.2 | 0.835737 | 4(Loss) | true |
| simdjson (ondemand) | 989.969 | 0.745477 | 5903.89ms | 56369 | 160 | 2.62197e+07 | 54302.4 | 0.0382893 | 5(Loss) | true |
