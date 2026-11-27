
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 509.159 | 2.18305 | 6197.8ms | 2251027 | 80 | 6.77753e+11 | 4.21626e+06 | 1.57331 | 4.86218 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 500.688 | 1.08176 | 6617.66ms | 2251027 | 80 | 1.72101e+11 | 4.2876e+06 | 6.60238 | 4.94443 | -(Tie) | false |
| simdjson (ondemand) | 184.763 | 1.23221 | 8321.46ms | 2251027 | 40 | 8.19897e+11 | 1.16189e+07 | 0.603562 | 13.3995 | 3(Loss) | true |
| Glaze | 168.346 | 0.524242 | 9000.72ms | 2251027 | 40 | 1.78764e+11 | 1.2752e+07 | 0.420342 | 14.7066 | 4(Loss) | true |
