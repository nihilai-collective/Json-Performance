
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2412.56 | 0.207702 | 10116ms | 7351818 | 160 | 5.82954e+09 | 2.90614e+06 | 0.570004 | 1.02619 | 1(Win) | true |
| Jsonifier | 2228.33 | 0.643952 | 5148.69ms | 7351818 | 40 | 1.64209e+10 | 3.14641e+06 | 1.30016 | 1.11104 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 788.731 | 0.345059 | 6554.56ms | 7351818 | 30 | 2.82254e+10 | 8.88927e+06 | 2.66047 | 3.13894 | -(Loss) | false |
| simdjson (ondemand) | 511.344 | 0.159852 | 9933.79ms | 7351818 | 40 | 1.92159e+10 | 1.37114e+07 | 0.343164 | 4.84169 | 4(Loss) | true |
