
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2656.32 | 0.167409 | 6906.88ms | 183677 | 320 | 3.89994e+06 | 65944 | 0.106871 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2650.59 | 0.262211 | 6776.41ms | 183677 | 160 | 4.80449e+06 | 66086.4 | 0.501241 | 1(Tie) | true |
| Glaze | 2271.52 | 0.11603 | 8023.89ms | 183677 | 640 | 5.12383e+06 | 77114.8 | 0.0150448 | 3(Loss) | true |
| simdjson (reflection) | 2062.91 | 0.293798 | 8708.44ms | 183677 | 1280 | 7.96629e+07 | 84913 | 0.672609 | 4(Loss) | true |
| simdjson (ondemand) | 1993.26 | 0.078962 | 9173.84ms | 183677 | 1280 | 6.16352e+06 | 87880.2 | 0.137952 | 5(Loss) | true |
